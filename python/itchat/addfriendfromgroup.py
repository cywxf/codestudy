#coding=utf-8
import itchat, time, random
itchat.auto_login(enableCmdQR=2, hotReload=True)
def get_chatroom(chatroomUserName = '1234567'):
    itchat.get_chatrooms(update=True)
    chatrooms = itchat.search_chatrooms(chatroomUserName);
    if chatrooms:
        return chatrooms[0]
    else:
        return None

def get_newusers(chatroom):
    chatroom = itchat.update_chatroom(chatroom['UserName'])
    newusers = []
    for friend in chatroom['MemberList']:
        #print("friend name is : %s " % (friend['DisplayName'] or friend['NickName']))
        existfriend = itchat.search_friends(userName=friend['UserName'])
        if existfriend is not None:
            print('%s is in the friend list' % (friend['DisplayName'] or friend['NickName']))
            pass
        else:
            newusers.append(friend)
    return newusers

def add_users(chatroom):
    newusers = get_newusers(chatroom)
    if 'USTC' in chatroom['NickName']:
        VerifyContent = 'Hi, I am Qiao Xu 0804 from %s' % chatroom['NickName']
    else:
        VerifyContent = 'Hi, I am Qiao Xu from %s' % chatroom['NickName']
    random.shuffle(newusers) #random shuffle elements
    iadded = 0
    for friend in newusers:
        #if friend['NickName'] != 'test': continue  # a specific name
        add_msg = itchat.add_friend(friend['UserName'], status=2, verifyContent=VerifyContent, autoUpdate=True)
        #print("Adding %s now: %s" % (friend['NickName'], add_msg['BaseResponse']['ErrMsg'].encode('latin-1')))
        try:
            add_msg['BaseResponse']['ErrMsg'].encode('latin-1')
            print("Adding %s now: %s" % (friend['NickName'], add_msg['BaseResponse']['ErrMsg'].encode('latin-1')))
        except:
            print("Adding %s now: %s" % (friend['NickName'], add_msg['BaseResponse']['ErrMsg']))
            pass
        iadded = iadded + 1
        itry = 0
        while add_msg['BaseResponse']['ErrMsg'] != u'请求成功':  # api limitation, only 10 at a time
        #while add_msg['BaseResponse']['ErrMsg'].encode('latin-1') == '操作太频繁，请稍后再试。':  # api limitation, only 10 at a time
            itry = itry + 1
            time.sleep(100)
            add_msg = itchat.add_friend(friend['UserName'], status=2, verifyContent=VerifyContent, autoUpdate=True)
            print('retry %s time' % itry)
        time.sleep(30)
    return iadded

def main():
    #for chatroom in itchat.get_chatrooms(update=True):
    #    print ('%s : %s members' % (chatroom['NickName'], len(chatroom['MemberList'])))

    #chatroom=get_chatroom(u'琪石朋友圈')
    #chatroom=get_chatroom(u'纳城华人帮')
    #chatroom=get_chatroom('USTC-AAGNY-Summit')
    #chatroom=get_chatroom(u'石溪租房群#2')
    #chatroom=get_chatroom(u'琪石2017高级会员群')
    chatroom = get_chatroom(u'2017 USTC春节聚会')
    if chatroom is None:
        pass
    else:
        print(chatroom['NickName'] + ', Total %s members' % len(chatroom['MemberList']))
        print('adding %d new users' % add_users(chatroom))

    #for chatroom in itchat.get_chatrooms(): #All chatrooms, be careful when using this
    #    print(chatroom['NickName'] + ', Total %s members' % len(chatroom['MemberList']))
    #    print('adding %d new users' % add_users(chatroom))

if __name__ == "__main__":
    main()
