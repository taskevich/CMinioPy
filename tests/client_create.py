import time

from cminiopy import CMinio

c = CMinio(
    "localhost:9000",
    "adminadmin",
    "passwordpassword",
    False
)

c.list_objects("d3319d72", "files/")
