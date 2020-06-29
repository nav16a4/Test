#ifndef APP_H
#define APP_H

namespace My { class Network; }


class App
{
public:
    virtual void SetupApp();
    virtual void StartApp();
protected:
    My::Network* m_Network;
};
class ServerApp : public App
{
public:
    virtual void StartApp();
};

class ClientApp : public App
{
    virtual void SetupApp();
    virtual void StartApp();
};
#endif // !APP_H
