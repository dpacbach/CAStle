ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,IFACE)
else
    $(call make_so,IFACE,castleiface)
endif
