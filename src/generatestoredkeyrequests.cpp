#include "generatestoredkeyrequests.h"
#include "utils.h"

#include <Sailfish/Crypto/generatestoredkeyrequest.h>

#include <QtCore/QDebug>

using namespace Sailfish::Crypto;

namespace {

    RsaKeyPairGenerationParameters CreateGenParams(const std::size_t keyLength)
    {
        RsaKeyPairGenerationParameters result;
        result.setModulusLength(keyLength);
        return result;
    }

} // anonymous namespace

Sailfish::Crypto::Key GenerateStoredKeyRequests::createStoredKey(
    const QString& keyName,
    const QString& collectionName,
    const QString& dbName,
    const Sailfish::Crypto::CryptoManager::Algorithm algorithm,
    const Sailfish::Crypto::CryptoManager::Operations operations,
    const std::size_t keyLength)
{
    qDebug() << Q_FUNC_INFO;

    Key key;
    key.setAlgorithm(algorithm);
    key.setSize(keyLength);
    key.setOrigin(Key::OriginDevice);
    key.setOperations(operations);
    key.setIdentifier(Key::Identifier(keyName, collectionName, dbName));
    key.setComponentConstraints(
        Sailfish::Crypto::Key::MetaData |
        Sailfish::Crypto::Key::PublicKeyData |
        Sailfish::Crypto::Key::PrivateKeyData);

    CryptoManager manager;
    GenerateStoredKeyRequest request;
    request.setManager(&manager);
    request.setKeyTemplate(key);
    request.setCryptoPluginName(CryptoManager::DefaultCryptoPluginName);
    if (algorithm == Sailfish::Crypto::CryptoManager::AlgorithmRsa) {
        request.setKeyPairGenerationParameters(CreateGenParams(key.size()));
    }
    request.startRequest();
    request.waitForFinished();

    if (not IsRequestWasSuccessful(&request)) {
        qDebug() << "Error when generating key";
        throw std::runtime_error("Error when generating key");
    }

    return request.generatedKeyReference();
}