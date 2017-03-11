ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
else
    $(call make_so,CASCREATION,castlecascreation)

    locations := parsers
    $(call enter_all,$(locations))
endif
