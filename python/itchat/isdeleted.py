#coding=utf-8
import itchat, time
itchat.auto_login(enableCmdQR=2, hotReload=True)
chatroomUserName = '1234567'

for friend in itchat.get_friends()[:2]:
    print(friend['NickName'] or friend['UserName'])
    chatroom = itchat.add_member_into_chatroom(chatroomUserName, [friend])
    chatroom = itchat.update_chatroom(r['UserName'])
    if r['BaseResponse']['ErrMsg'] == '':
        if len(chatroom['MemberList']) == 0:
            print(u'No member in the chatroom')
        else:
            status = chatroom['MemberList'][0]['MemberStatus']
            itchat.delete_member_from_chatroom(chatroom['UserName'], [friend])
            if status == 3:
                print(u'该好友已经将你加入黑名单。')
            elif status == 4:
                print(u'该好友已经将你删除。')
            else:
                print(get(status) + u'该好友仍旧与你是好友关系。')
#itchat.run()
