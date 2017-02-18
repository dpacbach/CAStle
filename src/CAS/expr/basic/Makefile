ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASEXPRBASIC)
else
    $(call make_so,CASEXPRBASIC,castlecasexprbasic)
endif
