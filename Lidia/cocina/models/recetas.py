# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Recetas(models.Model):
    _name = 'cocina.recetas'
    _description = 'cocina recetas'

    nombre = fields.Char(string="Nombre Receta", size=60, required=True, help="Nombre de nuestra receta")
    descripcion = fields.Char(string="Descripcion", help="Descripcion de nuestra receta")
    ingredientes_ids = fields.Many2many("cocina.ingredientes", string="Lista de ingredientes")
    cursos_ids = fields.Many2many("cocina.cursos", string="Lista de cursos")