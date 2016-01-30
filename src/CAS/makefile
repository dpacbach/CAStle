ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    #$(call set_default_goal,CASNUMBER)
else
    $(call make_so,CASNUMBER,castlecasnumber)

    $(call enter,default)
endif
