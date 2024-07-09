#ifndef CONTACTS_HANDLER_HPP
#define CONTACTS_HANDLER_HPP
#include <box2d/box2d.h>

class ContactsHandler : public b2ContactListener, public b2ContactFilter
{
private:
public:
    ContactsHandler();
    ~ContactsHandler();
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
};

#endif