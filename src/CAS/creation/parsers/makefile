ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASCREATIONPARSERS)
else
    $(call make_so,CASCREATIONPARSERS,castlecascreationparsers)
endif
