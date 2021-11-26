# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Clases(models.Model):
     _name = 'upococinacopia.clases'
     _description = 'upococinacopia clases'

     nombreClase = fields.Char(string="Nombre Clase", size=60, required=True, help="Nombre de nuestra clase")
     fechaInicio = fields.Datetime('Fecha inicio',required=True, autodate = True)
     fechaFin = fields.Datetime('Fecha fin',required=True, autodate = True)
     aula_ids = fields.Many2one("upococinacopia.aulas",string="Lista de aulas")