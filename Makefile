include ./config.mk

default:
	make -C $(COMMON)/logManage
	make -C $(SERVER)
	make -C $(CLIENT)/clientMain

clean:
	make -C $(COMMON)/logManage    clean
	make -C $(SERVER)              clean
	make -C $(CLIENT)/clientMain   clean