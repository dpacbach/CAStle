ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASVISITING)
else
    $(call make_so,CASVISITING,castlecasvisiting)

    locations := numeval rendering restructuring
    $(call enter_all,$(locations))
endif
