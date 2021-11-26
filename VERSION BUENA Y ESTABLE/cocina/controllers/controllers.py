# -*- coding: utf-8 -*-
# from odoo import http


# class Cocina(http.Controller):
#     @http.route('/cocina/cocina/', auth='public')
#     def index(self, **kw):
#         return "Hello, world"

#     @http.route('/cocina/cocina/objects/', auth='public')
#     def list(self, **kw):
#         return http.request.render('cocina.listing', {
#             'root': '/cocina/cocina',
#             'objects': http.request.env['cocina.cocina'].search([]),
#         })

#     @http.route('/cocina/cocina/objects/<model("cocina.cocina"):obj>/', auth='public')
#     def object(self, obj, **kw):
#         return http.request.render('cocina.object', {
#             'object': obj
#         })
