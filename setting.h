#ifndef SETTING_H
#define SETTING_H


class UserSetting
{
public:
    UserSetting();
    bool isAutoSignin()const;
    bool isRemPassword()const;
    void setAutoSign(bool a);
    void setRemPassword(bool r);
    void setUserID(int userid);
    int getUserID(void)const;
private:
    bool autoSignin;
    bool remPassword;
    int UserID;
};

#endif // SETTING_H
