ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,PARSERS)
else
    $(call make_so,PARSERS,castleparsers)

    $(call enter,default)
endif
