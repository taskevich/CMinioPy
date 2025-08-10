import time

from cminiopy import CMinio

c = CMinio(
    "10.1.1.14:9000",
    "adminadmin",
    "passwordpassword",
    False
)

# c = CMinio(
#     "localhost:9001",
#     "minioadmin",
#     "minioadmin",
#     False
# )

start = time.time()
try:
    for o in c.list_objects("d3319d72-1be2-4e60-9586-5e4e39587891", "screenshot/", True):
        pass
except:
    pass
# for o in c.list_objects("test", "files/", True):
#     print(o)
print("time", time.time() - start)
