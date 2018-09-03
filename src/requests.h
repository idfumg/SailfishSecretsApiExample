#pragma once

#include <Sailfish/Crypto/key.h>

namespace Sailfish {
    namespace Crypto {
        class Request;
    }
}

class Requests : public QObject {
    Q_OBJECT

public:
    void getRandomData() const;
    void seedRandomGenerator() const;
    bool isCollectionExists() const;
    bool deleteCollection() const;
    bool createCollection() const;
    Sailfish::Crypto::Key createTemplateKey() const;
    Sailfish::Crypto::Key createStoredKey(const Sailfish::Crypto::Key& keyTemplate) const;
    QByteArray createIV(const Sailfish::Crypto::Key& key) const;
    QByteArray encrypt(const Sailfish::Crypto::Key& key,
                       const QByteArray& iv,
                       const QByteArray& plainText) const;
    QByteArray decrypt(const Sailfish::Crypto::Key& key,
                       const QByteArray& iv,
                       const QByteArray& cipherText) const;
    Sailfish::Crypto::Key getStoredKey() const;
    void pluginInfo() const;
    bool deleteStoredKey() const;
    QByteArray cipherText(const Sailfish::Crypto::Key& key,
                          const QByteArray& iv,
                          const QByteArray& plainText) const;
    QByteArray decipherText(const Sailfish::Crypto::Key& key,
                            const QByteArray& iv,
                            const QByteArray& ciphertext) const;
    QByteArray sign(const Sailfish::Crypto::Key& key,
                    const QByteArray& data) const;
};
