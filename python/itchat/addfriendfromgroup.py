#coding=utf-8
import itchat, time
itchat.auto_login(enableCmdQR=2, hotReload=True)
def get_chatroom(chatroomUserName = '1234567'):
    itchat.get_chatrooms(update=True)
    chatrooms = itchat.search_chatrooms(chatroomUserName);
    if chatrooms:
        return chatrooms[0]
    else:
        return None

def add_users(chatroom, maxwanting=5):
    chatroom = itchat.update_chatroom(chatroom['UserName'])
    newusers = 0
    for friend in chatroom['MemberList']:
        #print("friend name is : %s " % (friend['DisplayName'] or friend['NickName']))
        existfriend = itchat.search_friends(userName=friend['UserName'])
        if existfriend is not None:
            print('%s is in the friend list' % (friend['DisplayName'] or friend['NickName']))
            pass
        elif newusers < maxwanting: # first n non-friend
        #elif friend['NickName'] == 'test': # some specify friend, for test use
            add_msg = itchat.add_friend(friend['UserName'], status=2, verifyContent='Hi, I am Qiao Xu 0804 from %s' % chatroom['NickName'], autoUpdate=True)
            print("Adding %s now: %s, raw: %s" % (friend['NickName'], add_msg['BaseResponse']['ErrMsg'], add_msg['BaseResponse']['RawMsg']))
            newusers = newusers + 1
    return newusers

#chatroom=get_chatroom(u'琪石朋友圈')
#chatroom=get_chatroom(u'纳城华人帮')
chatroom=get_chatroom('USTC-AAGNY-Summit')
print(chatroom['NickName'] + ', Total %s members' % len(chatroom['MemberList']))
print('adding %d new users' % add_users(chatroom, 500))
#for chatroom in itchat.get_chatrooms(): #All chatrooms, be careful when using this
#    print(chatroom['NickName'] + ', Total %s members' % len(chatroom['MemberList']))
#    print('adding %d new users' % add_users(chatroom))
