#include "setting.h"

UserSetting::UserSetting()
{

}

bool UserSetting::isAutoSignin()const
{
    return autoSignin;
}

bool UserSetting::isRemPassword()const
{
    return remPassword;
}

void UserSetting::setAutoSign(bool a)
{
    autoSignin = a;
}

void UserSetting::setRemPassword(bool r)
{
    remPassword = r;
}

void UserSetting::setUserID(int userid)
{
    UserID = userid;
}

int UserSetting::getUserID() const
{
    return UserID;
}
