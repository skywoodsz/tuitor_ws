import lcm
from type.exlcm import example_t

lc = lcm.LCM()
msg = example_t()
msg.timestamp = 0
msg.position = (1, 2, 3)
msg.orientation = (1, 0, 0, 0)
msg.ranges = range(15)
msg.num_ranges = len(msg.ranges)
msg.name = "example_string"
msg.enabled = True

lc.publish("EXAMPLE", msg.encode())


