# -*- coding: utf-8 -*-
# from odoo import http


# class Cocinaextension(http.Controller):
#     @http.route('/cocinaextension/cocinaextension/', auth='public')
#     def index(self, **kw):
#         return "Hello, world"

#     @http.route('/cocinaextension/cocinaextension/objects/', auth='public')
#     def list(self, **kw):
#         return http.request.render('cocinaextension.listing', {
#             'root': '/cocinaextension/cocinaextension',
#             'objects': http.request.env['cocinaextension.cocinaextension'].search([]),
#         })

#     @http.route('/cocinaextension/cocinaextension/objects/<model("cocinaextension.cocinaextension"):obj>/', auth='public')
#     def object(self, obj, **kw):
#         return http.request.render('cocinaextension.object', {
#             'object': obj
#         })
