# -*- coding: utf-8 -*-
# from odoo import http


# class GymExpansion(http.Controller):
#     @http.route('/gym_expansion/gym_expansion/', auth='public')
#     def index(self, **kw):
#         return "Hello, world"

#     @http.route('/gym_expansion/gym_expansion/objects/', auth='public')
#     def list(self, **kw):
#         return http.request.render('gym_expansion.listing', {
#             'root': '/gym_expansion/gym_expansion',
#             'objects': http.request.env['gym_expansion.gym_expansion'].search([]),
#         })

#     @http.route('/gym_expansion/gym_expansion/objects/<model("gym_expansion.gym_expansion"):obj>/', auth='public')
#     def object(self, obj, **kw):
#         return http.request.render('gym_expansion.object', {
#             'object': obj
#         })
