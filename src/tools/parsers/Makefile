ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
else
    $(call make_so,PARSERS,castleparsers)

    $(call enter,default)
endif
