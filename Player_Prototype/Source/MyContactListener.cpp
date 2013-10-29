#include "MyContactListener.h"


MyContactListener::MyContactListener()
{
    //ctor
}

void MyContactListener::BeginContact(b2Contact* contact)
{
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
      if ( (int)fixtureUserData == 3 )
      {
        numFootContacts++;
      }
      fixtureUserData = contact->GetFixtureB()->GetUserData();
      if ( (int)fixtureUserData == 3 )
      {
        numFootContacts++;
      }
}

void MyContactListener::EndContact(b2Contact* contact)
{
      void* fixtureUserData = contact->GetFixtureA()->GetUserData();
      if ( (int)fixtureUserData == 3 )
      {
            numFootContacts--;
      }
      fixtureUserData = contact->GetFixtureB()->GetUserData();
      if ( (int)fixtureUserData == 3 )
      {
            numFootContacts--;
      }
}
