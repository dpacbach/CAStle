ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASREDUCTION)
else
    $(call make_so,CASREDUCTION,castlecasreduction)
endif
