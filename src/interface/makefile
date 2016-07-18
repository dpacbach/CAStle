ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,IFACE)
else
    TP_INCLUDES_IFACE = -I$(HOME)/include
    $(call make_so,IFACE,castleiface)
endif
