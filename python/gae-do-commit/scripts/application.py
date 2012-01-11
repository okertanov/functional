import os
import sys
from google.appengine.ext import webapp
from google.appengine.ext.webapp.util import run_wsgi_app
from google.appengine.ext.webapp import template

class TemplateRenderer(object):
    def render(self, path, params):
        (head, tail) = os.path.split(os.path.dirname(__file__))
        vpath = os.path.join(head, path)
        return template.render(vpath, params)

#@RouteDef('/')
class MainRoute(webapp.RequestHandler):
    route = '/'
    def get(self, *args):
        content = TemplateRenderer().render('templates/main.htmp', {'title':'Main', 'huge':'.'})
        self.response.out.write(content)

#@RouteDef('/api')
class ApiRoute(webapp.RequestHandler):
    route  = '(/api/?)((?<=/).*)'
    route2 = '(/api)'
    def get(self, *args):
        endpoint = ''
        for arg in args: endpoint += arg
        self.response.headers['Content-Type'] = 'application/x-javascript'
        self.response.out.write('{ "command": "%(endpoint)s", "reply": "%(httpstatus)s" }' % {'endpoint':endpoint, 'httpstatus':'200 OK'})

#@RouteDef(r'/static/?.*')
class StaticRoute(webapp.RequestHandler):
    route = r'/static/?.*'
    def get(self, *args):
        self.redirect("/static/index.html")

def main():
    application = webapp.WSGIApplication(
            [
                (StaticRoute.route,  StaticRoute),
                (ApiRoute.route,     ApiRoute),
                (ApiRoute.route2,    ApiRoute),
                (MainRoute.route,    MainRoute)
            ],
            debug=True)
    run_wsgi_app(application)

if __name__ == "__main__":
    main()

