#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D/Box2D.h>

extern int numFootContacts;

class MyContactListener : public b2ContactListener
  {
      void BeginContact(b2Contact* contact) {
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

      void EndContact(b2Contact* contact) {
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
  };

#endif // MYCONTACTLISTENER_H
