#

I found that sigslot::has_slots class is not an interface in some situations, i.e., if the mt_policy is a multi_threaded_local, the has_slots class has a member of some kind of mutex.

So if you want to use a sigslot::has_slots class with multi_threaded_local mt_policy or some other you defined, make sure you do know what you are doing. 