# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Cursos(models.Model):
     _name = 'cocina.cursos'
     _description = 'cocina cursos'

     nombre = fields.Char(string="Nombre Curso", size=60, required=True, help="Nombre de nuestra curso")

     fechaInicio = fields.Datetime('Fecha inicio', help="Fecha de inicio de nuestro curso")
     fechaFin = fields.Datetime('Fecha fin', help="Fecha de finalizacion de nuestro curso")
     recetas_ids = fields.Many2many("cocina.recetas", string="Lista de recetas")