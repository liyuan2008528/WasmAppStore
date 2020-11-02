package com.ctd.teeagent.util;

import android.content.Context;

import org.bouncycastle.asn1.ASN1ObjectIdentifier;
import org.bouncycastle.asn1.x9.ECNamedCurveTable;
import org.bouncycastle.asn1.x9.X9ECParameters;
import org.bouncycastle.jce.provider.BouncyCastleProvider;
import org.bouncycastle.openssl.PEMKeyPair;
import org.bouncycastle.openssl.PEMParser;
import org.bouncycastle.openssl.jcajce.JcaPEMKeyConverter;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.Principal;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Security;
import java.security.Signature;
import java.security.SignatureException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateExpiredException;
import java.security.cert.CertificateFactory;
import java.security.cert.CertificateNotYetValidException;
import java.security.cert.X509CRL;
import java.security.cert.X509CRLEntry;
import java.security.cert.X509Certificate;
import java.security.spec.ECGenParameterSpec;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.Iterator;
import java.util.Set;

public class CertificateUtils {

    public static String ALGORITHM = "algorithm";
    public static String PK_ALG_NAME = "pubkeyAlgName";

    // 是否开启证书注销链检查
    private static final boolean OPEN_CRL_CHECK = false;

    /**
     * 加载CRL证书吊销列表文件
     *
     * @param crlFilePath
     * @return
     * @throws Exception
     */
    public static X509CRL loadX509CRL(String crlFilePath) throws Exception {
        FileInputStream in = new FileInputStream(crlFilePath);
        CertificateFactory cf = CertificateFactory.getInstance("X.509");
        X509CRL crl = (X509CRL) cf.generateCRL(in);
        in.close();
        return crl;
    }


    /**
     * 证书是否过期
     *
     * @param cert
     * @return false 未过期，true 证书过期
     */
    public static boolean isExpire(X509Certificate cert) {
        try {
            cert.checkValidity(new Date());
        } catch (CertificateExpiredException e) {
            return true; // 已过期
        } catch (CertificateNotYetValidException e) {

            return true; // 无效证书
        }
        return false; //未过期
    }

    /**
     * 读取cert证书
     *
     * @param certContent
     * @throws CertificateException
     */
    public static X509Certificate readCert(byte[] certContent) throws CertificateException {
        CertificateFactory cf = CertificateFactory.getInstance("X.509");
        X509Certificate cert = (X509Certificate) cf.generateCertificate(new ByteArrayInputStream(certContent));
        return cert;
    }

    /**
     * 证书链校验
     *
     * @param X509certificateRoot            CA 根证书，不必放入到待检测的证书链中
     * @param collectionX509CertificateChain 从根向子证书顺序添加，下一级证书通过上一级证书的公钥进行验证，待检测的证书最后添加
     * @param X509crl                        证书注销链
     * @param targetSubjectDN                最后一个证书的所有者是否为现在通信对象  cert subject Distinguished Name
     * @return
     */
    public static boolean verify(X509Certificate X509certificateRoot, Collection collectionX509CertificateChain, X509CRL X509crl, String targetSubjectDN) {
        //获取证书链长度
        int nSize = collectionX509CertificateChain.size();
        //将证书链转化为数组
        X509Certificate[] arX509certificate = new X509Certificate[nSize];
        collectionX509CertificateChain.toArray(arX509certificate);
        //声明list，存储证书链中证书主体信息
        ArrayList list = new ArrayList();
        //沿证书链自上而下，验证证书的所有者是下一个证书的颁布者
        Principal principalLast = null;
        for (int i = 0; i < nSize; i++) {//遍历arX509certificate
            X509Certificate x509Certificate = arX509certificate[i];
            //获取发布者标识
            Principal principalIssuer = x509Certificate.getIssuerDN();
            //获取证书的主体标识
            Principal principalSubject = x509Certificate.getSubjectDN();
            //保存证书的序列号
            list.add(x509Certificate.getSerialNumber());

            if (principalLast != null) {
                //验证证书的颁布者是上一个证书的所有者
                if (principalIssuer.equals(principalLast)) {
                    try {
                        //获取上个证书的公钥
                        PublicKey publickey = arX509certificate[i - 1].getPublicKey();
                        //验证是否已使用与指定公钥相应的私钥签署了此证书
                        arX509certificate[i].verify(publickey);
                    } catch (Exception e) {
                        return false;
                    }
                } else {
                    return false;
                }
            }
            principalLast = principalSubject;

        }

        if (OPEN_CRL_CHECK) {
            //验证根证书是否在撤销列表中
            try {
                if (!X509crl.getIssuerDN().equals(X509certificateRoot.getSubjectDN())) return false;
                X509crl.verify(X509certificateRoot.getPublicKey());
            } catch (Exception e) {
                return false;
            }
            //在当前时间下，验证证书链中每个证书是否存在撤销列表中
            if (X509crl != null) {
                try {
                    //获取CRL中所有的项
                    Set setEntries = X509crl.getRevokedCertificates();

                    if (setEntries == null && setEntries.isEmpty() == false) {
                        Iterator iterator = setEntries.iterator();
                        while (iterator.hasNext()) {
                            X509CRLEntry X509crlentry = (X509CRLEntry) iterator.next();

                            if (list.contains(X509crlentry.getSerialNumber())) return false;
                        }
                    }
                } catch (Exception e) {
                    return false;
                }
            }
        }

        //证明证书链中的第一个证书由用户所信任的CA颁布
        try {
            PublicKey publickey = X509certificateRoot.getPublicKey();
            arX509certificate[0].verify(publickey);
        } catch (Exception e) {
            return false;
        }
        //证明证书链中的最后一个证书的所有者正是现在通信对象
        Principal principalSubject = arX509certificate[nSize - 1].getSubjectDN();
        if (!targetSubjectDN.equals(principalSubject.getName())) return false;
        //验证证书链里每个证书是否在有效期里
        Date date = new Date();
        for (int i = 0; i < nSize; i++) {
            try {
                arX509certificate[i].checkValidity(date);
            } catch (Exception e) {
                return false;
            }
        }
        return true;
    }


    /**
     * 从pem文件中读取公私钥
     *
     * @return
     */
    public static KeyPair getKeyPairFromPem(Context context) {
        try {
            Security.removeProvider(BouncyCastleProvider.PROVIDER_NAME);
            if (Security.getProvider(BouncyCastleProvider.PROVIDER_NAME) == null) {
                Security.addProvider(new BouncyCastleProvider());
            }
            InputStream in = context.getApplicationContext().getAssets().open("SK_TAM_ECDSA_NIST.pem");   // 这个puk.crt文件可以是16进制的也可以是Base64后的
            Reader fRd = new BufferedReader(new InputStreamReader(in));
            Security.addProvider(new BouncyCastleProvider());
            PEMParser pemRd = new PEMParser(fRd);
            PEMKeyPair pemPair;
            KeyPair pair;
            ASN1ObjectIdentifier ecOID = (ASN1ObjectIdentifier) pemRd.readObject();
            X9ECParameters ecSpec = ECNamedCurveTable.getByOID(ecOID);
            if (ecSpec == null) {
                throw new Exception("ecSpec not found for named curve");
            }
            pemPair = (PEMKeyPair) pemRd.readObject();
            pair = new JcaPEMKeyConverter().setProvider("BC").getKeyPair(pemPair);
            return pair;


        } catch (NoSuchAlgorithmException | NoSuchProviderException e) {
            e.printStackTrace();
        } catch (CertificateException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return null;
    }


    public static KeyPair generatorKeyPair() {

        KeyPair pair = null;
        try {
            KeyPairGenerator g = KeyPairGenerator.getInstance("EC");
            ECGenParameterSpec kpgparams = new ECGenParameterSpec("secp256r1");
            g.initialize(kpgparams);
            pair = g.generateKeyPair();


        } catch (InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return pair;
    }


    public static byte[] sign(PrivateKey privateKey, String msg) {

        Signature ecdsaSign = null;
        try {
            ecdsaSign = Signature.getInstance("SHA256withECDSA");
            ecdsaSign.initSign(privateKey);
            ecdsaSign.update(msg.getBytes());
            byte[] sign = ecdsaSign.sign();
            return sign;
        } catch (NoSuchAlgorithmException | InvalidKeyException | SignatureException e) {
            e.printStackTrace();
        }
        return null;

    }


    /**
     * ES256验签
     * @param publicKey
     * @param msg
     * @param signature
     * @return
     */
    public static boolean es256ValidationSign(PublicKey publicKey, String msg,byte[] signature) {

        try {
            Signature ecdsaSign = Signature.getInstance("SHA256withECDSA");
            // Validation
            ecdsaSign.initVerify(publicKey);
            ecdsaSign.update(msg.getBytes());
            if (ecdsaSign.verify(signature))
                return true;
            else
                return false;
        } catch (NoSuchAlgorithmException | InvalidKeyException | SignatureException e) {
            e.printStackTrace();
        }
        return false;

    }





}
