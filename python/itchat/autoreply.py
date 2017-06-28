#coding=utf-8
import itchat, requests
@itchat.msg_register(itchat.content.TEXT)
def reply(msg):
    reply = ''
    friend = itchat.search_friends(userName = msg['FromUserName'])
    ownAccount = itchat.get_friends(update=True)[0]
    if friend['UserName'] == ownAccount['UserName']:
        #return u'Own account'
        return u'还是同样的雨天，还是相同的地点，在转角的咖啡馆，我又再一次遇到了那张我永远忘不掉的脸。四目相对，终于，她颤抖地问我，你还可以像以前一样牵着我过马路吗？我说：“奶奶，上次你走到马路中间就躺下了，讹了我几个月的工资啊 ！”'
    elif friend is None:
        return u'Not a friend'
    elif friend.get('NickName') in  [u'风早',u'Lemon']:
        reply = ' test autoreply '
    return reply # or defaultReply

itchat.auto_login(hotReload=True, enableCmdQR=2)
itchat.run()
