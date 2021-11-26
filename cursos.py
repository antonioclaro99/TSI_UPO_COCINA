# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Cursos(models.Model):
     _name = 'cocina.cursos'
     _description = 'cocina cursos'

     nombre = fields.Char(string="Nombre Curso", size=60, required=True, help="Nombre de nuestra curso")

     fechaInicio = fields.Date('Fecha inicio', help="Fecha de inicio de nuestro curso")
     fechaFin = fields.Date('Fecha fin', help="Fecha de finalizacion de nuestro curso")
     clases_ids = fields.Many2one("cocina.clases",string="Lista de clases")
     chef_id = fields.Many2one("cocina.chefs",string="Chef que imparte el curso")
     alumnos_id = fields.Many2many("cocina.alumnos",string="Lista de alumnos")