ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,PARSERS)
else
    $(call make_so,PARSERS,castleparsers)

    $(call enter,default)
endif
