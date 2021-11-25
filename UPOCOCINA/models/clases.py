# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Clases(models.Model):
     _name = 'upoCocina.clases'
     _description = 'upoCocina clases'

     nombreClase = fields.Char(string="Nombre Clase", size=60, required=True, help="Nombre de nuestra clase")
     fechaInicio = fields.Date('Fecha inicio', help="Fecha de inicio de nuestra clase")
     fechaFin = fields.Date('Fecha fin', help="Fecha de finalizacion de nuestra clase")
     aula_ids = fields.Many2one("upoCocina.aulas",string="Lista de aulas")