ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
else
    $(call set_location,CAS)
    # Must enter in order of dependencies.
    locations := number expr rendering reduction
    $(call enter_all,$(locations))
endif
