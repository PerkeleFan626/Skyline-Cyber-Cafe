#include "SessionManager.h"
#include <iostream>

using namespace std;

SessionManager::SessionManager(DataManager& dataMgr, TransactionManager& transMgr)
    : dbManager(dataMgr), transManager(transMgr) {}

bool SessionManager::start_new_session(int userId) {
    UserSession blankSession;
    blankSession.userId = userId;
    blankSession.internetMinutes = 0;
    blankSession.gamingMinutes = 0;
    blankSession.printsCount = 0;
    blankSession.scansCount = 0;

    if (dbManager.add_active_session(blankSession)) {
        cout << "Terminal Session Activated for User ID: " << userId << endl;
        return true;
    }
    return false;
}


bool SessionManager::simulate_activity(int userId, int addInternet, int addGaming, int addPrints, int addScans) {
    vector<UserSession> activeSessions = dbManager.get_all_sessions();
    bool sessionFound = false;

    for (auto& session : activeSessions) {
        if (session.userId == userId) {
            session.internetMinutes += addInternet;
            session.gamingMinutes += addGaming;
            session.printsCount += addPrints;
            session.scansCount += addScans;

            dbManager.add_active_session(session);
            sessionFound = true;
            cout << "Activity Recorded: User " << userId << " metrics modified \n";
            break;
        }
    }

    if (!sessionFound) {
        if (!sessionFound) {
            cout << "Error: Cannot log activity. No active session found for User ID: " << userId << endl;
        }
        return sessionFound;
    }

}

bool SessionManager::end_and_checkout_session(int userId) {
    vector<UserSession> activeSessions = dbManager.get_all_sessions();

    for (const auto& session : activeSessions) {
        if (session.userId == userId) {
            bool paymentProcessed = transManager.process_session_checkout(
                session.userId,
                session.internetMinutes,
                session.gamingMinutes,
                session.printsCount,
                session.scansCount
            );

            if (paymentProcessed) {
                dbManager.remove_active_session(userId);
                cout << "Active tracking row for User " << userId << " scrubbed from terminal sheets.\n";
                return true;
            }
            return false;
        }
    }
    cout << "Error: Checkout failed. User " << userId << " does not have an open terminal session.\n";
    return false;
}