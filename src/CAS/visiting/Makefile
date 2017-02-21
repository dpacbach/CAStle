ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITING)
else
    $(call make_so,CASVISITING,castlecasvisiting)
endif
