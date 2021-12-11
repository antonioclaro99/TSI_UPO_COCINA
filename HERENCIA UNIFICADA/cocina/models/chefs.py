# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Chefs(models.Model):
    _name ='cocina.chefs'
    _inherit = 'cocina.personas'

    especialidad  = fields.Char("Especialidad" ,required=True)
    sueldo  = fields.Float("Sueldo Mensual")

    #cursos_ids = fields.One2many("upo_cocina.cursos",string="Cursos Confirmados")