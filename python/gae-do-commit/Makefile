
all: update

update:
	-@cmd /C 'appcfg.py --verbose --email=okertanov@gmail.com update .'

update_cron:
	-@cmd /C 'appcfg.py update_cron .'

update_dos:
	-@cmd /C 'appcfg.py update_dos .'

get_logs:
	-@cmd /C 'appcfg.py request_logs --severity=0 --include_vhost --append . logs/application.log'

cron_info:
	-@cmd /C 'appcfg.py cron_info .'

clean:

.PHONY: all clean update

.SILENT: clean

