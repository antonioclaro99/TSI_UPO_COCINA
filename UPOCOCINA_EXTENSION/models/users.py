# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Users(models.Model):
     _inherit = 'gym.users'

     materiales_ids = fields.Many2many("gym_expansion.materiales",string="Used material")