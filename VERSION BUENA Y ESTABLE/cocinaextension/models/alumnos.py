# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Alumnos(models.Model):
    _name ='cocinaextension.alumnos'
    _inherit = 'cocina.personas'

    id_alumno = fields.Integer("idAlumno")
    descuento = fields.Boolean("Descuento")

    cursos_ids = fields.Many2many("cocina.cursos",string="Cursos Confirmados")