#include "dllrestapi.h"

DLLRestAPI::DLLRestAPI()
{
    objectEngineClass = new EngineClass;
    connect(objectEngineClass, SIGNAL(gotInfo()), this, SLOT(gotInfoSlot()));
    connect(objectEngineClass, SIGNAL(loginSignal(QString)), this, SLOT(loginSlot(QString)));
    connect(objectEngineClass, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(objectEngineClass, SIGNAL(successSignal(QString)), this, SLOT(successSlot(QString)));
}

DLLRestAPI::~DLLRestAPI()
{
    delete objectEngineClass;
    objectEngineClass = nullptr;
}

QString DLLRestAPI::getBalance(){
   return QString::number(objectEngineClass->getBalance(), 'f', 2);
}

QString DLLRestAPI::getCryptoBalance(){
   return QString::number(objectEngineClass->getCryptoBalance(), 'f', 8);
}

QString DLLRestAPI::getRate(){
    return QString::number(objectEngineClass->getRate(), 'f', 5);
}

void DLLRestAPI::login(QString card, QString pin)
{
    objectEngineClass->login(card, pin);
}

void DLLRestAPI::logout()
{
    objectEngineClass->logout();
}

void DLLRestAPI::withdrawMoney(QString amount)
{
    objectEngineClass->withdrawMoney(amount);
}

void DLLRestAPI::buyCrypto(QString amount)
{
    objectEngineClass->buyCrypto(amount);
}

void DLLRestAPI::sellCrypto(QString amount)
{
    objectEngineClass->sellCrypto(amount);
}

void DLLRestAPI::transferMoney(QString recipient, QString amount)
{
    objectEngineClass->transferMoney(recipient, amount);
}

bool DLLRestAPI::accountExists(QString account){
    return objectEngineClass->accountExists(account);
}

QString DLLRestAPI::getName(){
    return objectEngineClass->getName();
}

QString DLLRestAPI::getAddr(){
    return objectEngineClass->getAddr();
}

QString DLLRestAPI::getPhone(){
    return objectEngineClass->getPhone();
}

void DLLRestAPI::gotInfoSlot(){
    emit infoReceived();
}

void DLLRestAPI::loginSlot(QString response){
    emit loginSignal(response);
}

void DLLRestAPI::successSlot(QString response){
    emit successSignal(response);
}

void DLLRestAPI::errorSlot(QString response){
    emit errorSignal(response);
}

QString DLLRestAPI::getRecent(int n1, int n2)
{
    return objectEngineClass->getRecent(QString::number(n1), QString::number(n2));
}

void DLLRestAPI::lockCard(QString card){
    objectEngineClass->lockCard(card);
}


int DLLRestAPI::actionCount(){
    return objectEngineClass->actionCount();
}


