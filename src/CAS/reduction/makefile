ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASREDUCTION)
else
    $(call make_so,CASREDUCTION,castlecasreduction)
endif
