# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Materiales(models.Model):
     _name = 'gym_expansion.materiales'
     _description = 'Gym Materiales'

     name = fields.Char(string="Title", required=True, help="Nombre del material")
     quantity = fields.Integer("Quantity") 
     materialType = fields.Selection([('ropa','Ropa'),
                                     ('instrumentos','Instrumentos'),
                                     ('otros','Otros'),],
                                     'Type of material', default='instrumentos')
     users_ids = fields.Many2many("gym.users",string="Confirmed users")
     classes_ids = fields.Many2many("gym.classes",string="Confirmed classes")