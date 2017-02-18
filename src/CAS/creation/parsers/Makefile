ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASCREATIONPARSERS)
else
    $(call make_so,CASCREATIONPARSERS,castlecascreationparsers)
endif
