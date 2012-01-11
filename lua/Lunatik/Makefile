## --------------------------------------------------
## Makefile - maintenance
## okertanov@gmail.com (c) 2010
## --------------------------------------------------

DATE=`date "+%F"`

all:
	-@echo "make game | mybot | archive | distrib | clean"

archive:	clean
	@7z a ./Lunatik-game-$(DATE).zip ./lua/* ./*.lua README.txt

distrib:	clean
	@tar czvf ./Lunatik-StarterKit-$(DATE).tgz \
		../Lunatik/lua/ \
		../Lunatik/*.lua \
		../Lunatik/README.txt \
		../Lunatik/Makefile \
		../Lunatik/run.cmd

mybot:
	$(MAKE) -C ./lua/

test:	mybot
	echo end | ./lua/MyBot

game:
	java -jar tools/PlayGame.jar maps/map98.txt 1000 200 log.txt \
		"lua MainBot.lua" \
		"java -jar example_bots/BullyBot.jar" \

#	| java -jar tools/ShowGame.jar

clean:
	-@rm -f ./Lunatik-*.zip ./Lunatik-*.tgz ./log.txt
	-@$(MAKE) -C ./lua/ clean



