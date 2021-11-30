# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Clases(models.Model):
    _name = 'cocina.clases'
    _description = 'cocina clases'
    _rec_name='nombreClase'

    nombreClase = fields.Char(string="Nombre Clase", size=60, required=True, help="Nombre de nuestra clase")
    fechaInicio = fields.Datetime("Fecha inicio", required=True, autodate=True)
    fechaFin = fields.Datetime("Fecha fin", required=True, autodate=True)
    aula_ids = fields.Many2one("cocina.aulas", string="Aula")
    cursos_ids= fields.Many2one('cocina.cursos', "Curso")

    
    _sql_constraints = [('clases_nombreClase_unique','UNIQUE (nombreClase)','El nombreClase debe ser único')]
    