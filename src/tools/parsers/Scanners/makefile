ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,SCANNERS)
else
    $(call make_so,SCANNERS,castlescanners)
endif
