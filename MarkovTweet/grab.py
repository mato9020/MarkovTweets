import twitter
import json
import re

api = twitter.Api(consumer_key="gkacjeUJwYYDlJjrw217eCJda", consumer_secret="bMeKx9yZ8zrL4JdYYOUsGULs0CftewuXGPWgzUUzJRGpk0B3bL",
                  access_token_key="133321930-sUGnoVAeRjPdrO5OP2hktHiplGyql8dZYRXXkppH",
                  access_token_secret="q6DPodpGBvCML4uRhebhschkuMFOhcJCJ3PFdfpwQ5PxE")


statuses = api.GetUserTimeline(screen_name='elonmusk',count=200)
print([str(s.text) for s in statuses])

print('\n\n\n\n\n\n\n')
result = ''
regex =[r"(?:https?://)",r"\w*@\w*",r"\w*&\w*",r"[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&//=]*)"]
i=0
for s in statuses:

    i=i+1
    print(s.text)
    print(i)
    result = result + '\n' + s.text

test_str=result

print(result)



for r in regex:
    matches = re.finditer(r, test_str)

    for matchNum, match in enumerate(matches, start=1):
        
        print ("Match {matchNum} was found at {start}-{end}: {match}".format(matchNum = matchNum, start = match.start(), end = match.end(), match = match.group()))
        
        for groupNum in range(0, len(match.groups())):
            groupNum = groupNum + 1
            
            print ("Group {groupNum} found at {start}-{end}: {group}".format(groupNum = groupNum, start = match.start(groupNum), end = match.end(groupNum), group = match.group(groupNum)))

    result = re.sub(r,'',result)


print('\n final result \n')
print(result)

with open("input.txt",'w',encoding='utf8',errors='ignore') as file:
    file.write(result)


