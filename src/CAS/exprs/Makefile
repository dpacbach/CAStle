ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASEXPRS)
else
    $(call make_so,CASEXPRS,castlecasexprs)
endif
