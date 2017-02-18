ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    #$(call set_default_goal,CASEXPR)
else
    $(call make_so,CASEXPR,castlecasexpr)

    locations := basic builders
    $(call enter_all,$(locations))
endif
